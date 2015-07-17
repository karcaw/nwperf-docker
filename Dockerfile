FROM ubuntu

MAINTAINER e@pnnl.gov

RUN apt-get update
RUN apt-get install -y tpp openssh-client screen figlet zsh
ADD presentation.tpp /
ADD go.sh /
ADD Dockerfile /
ADD screenrc /root/.screenrc
RUN chsh -s /usr/bin/zsh

CMD /go.sh

