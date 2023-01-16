from dataclasses import replace
import torch as ch
from ffcvx.pipeline.allocation_query import AllocationQuery
from ffcvx.pipeline.compiler import Compiler
import numpy as np
from typing import Callable
from assertpy import assert_that
from torch.utils.data import Dataset
import logging
import os
from assertpy import assert_that
from tempfile import NamedTemporaryFile
from multiprocessing import cpu_count

from ffcvx.pipeline.operation import Operation
from ffcvx.transforms.ops import ToTensor
from ffcvx.writer import DatasetWriter
from ffcvx.reader import Reader
from ffcvx.loader import Loader
from ffcvx.fields import IntField, FloatField, BytesField
from ffcvx.fields.basics import FloatDecoder
from ffcvx.pipeline.state import State

from test_writer import DummyDataset

numba_logger = logging.getLogger('numba')
numba_logger.setLevel(logging.WARNING)


class Doubler(Operation):

    def generate_code(self) -> Callable:
        def code(x, dst):
            dst[:] = x * 2
            return dst
        return code

    def declare_state_and_memory(self, previous_state: State):
        return (previous_state, AllocationQuery(previous_state.shape, previous_state.dtype, previous_state.device))

def test_basic_simple():
    length = 600
    batch_size = 8
    with NamedTemporaryFile() as handle:
        file_name = handle.name
        dataset = DummyDataset(length)
        writer = DatasetWriter(file_name, {
            'index': IntField(),
            'value': FloatField()
        })

        writer.from_indexed_dataset(dataset)

        Compiler.set_enabled(True)

        loader = Loader(file_name, batch_size, num_workers=min(5, cpu_count()), seed=17,
                        pipelines={
                            'value': [FloatDecoder(), Doubler(), ToTensor()],
                        })

        def cond(value):
            value = value[0]
            result = value < 1 and value >= 0.5
            return result

        filtered = loader.filter('value', cond)

        assert_that(len(filtered)).is_greater_than(0)
        for index, values in filtered:
            assert_that(values.shape[0]).is_equal_to(batch_size)
            assert_that(((values < 1) & (values >= 0.5)).all()).is_true()