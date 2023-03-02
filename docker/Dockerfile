FROM pytorch/pytorch:latest

RUN apt-get update && apt-get install -y --no-install-recommends \
        software-properties-common \
        build-essential \
        curl \
        git \
        ffmpeg

RUN conda create -y -n ffcv python=3.9 \
        cupy \
        pkg-config \
        compilers \
        libjpeg-turbo \
        opencv \
        tqdm \
        terminaltables \
        assertpy \
        psutil \
        numpy=1.23.5 \
        numba \
        pytorch \
        torchvision \
        pytorch-cuda=11.7 -c pytorch -c nvidia -c conda-forge --no-channel-priority

RUN echo "source activate" >> ~/.bashrc
RUN echo "conda activate ffcv" >> ~/.bashrc

RUN git clone https://github.com/warner-benjamin/ffcv.git

RUN conda run -n ffcv pip install ffcv

# To test:
# 1- build the Dockerfile (e.g. docker build -t ffcv .)
# 2- login to the docker container (e.g. docker run -it --gpus all ffcv bash)
# 3- cd ffcv/examples/cifar
# 4- bash train_cifar.sh