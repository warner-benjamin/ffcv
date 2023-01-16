FROM pytorch/pytorch:latest

RUN apt-get update && apt-get install -y --no-install-recommends \
        software-properties-common \
        build-essential \
        curl \
        git \
        ffmpeg

RUN conda create -y -n ffcvx python=3.9 \
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
RUN echo "conda activate ffcvx" >> ~/.bashrc

RUN git clone https://github.com/warner-benjamin/ffcvx.git

RUN conda run -n ffcvx pip install ffcvx

# To test:
# 1- build the Dockerfile (e.g. docker build -t ffcvx .)
# 2- login to the docker container (e.g. docker run -it --gpus all ffcvx bash)
# 3- cd ffcvx/examples/cifar
# 4- bash train_cifar.sh