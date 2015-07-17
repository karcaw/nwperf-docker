--author Evan Felix
--title Docker for NWPerf
--date today
A short presentation on docker and how we are using it to run the NWPerf collection system.

--center http://docker.com
--center http://chef.io
--sethugefont slant
--newpage
--huge Why?

Because containers are awesome!

Docker containers wrap up a piece of software in a complete filesystem that contains everything it needs to run: code, runtime, system tools, system libraries -- anything you can install on a server. This guarantees that it will always run the same, regardless of the environment it is running in. (stolen from docker.com)

Not having to worry about what platforms each piece of nwperf is running on makes it much easier to manage and move around as we need to deploy new services.
--newpage
--huge Install
OSX - Kitematic: https://kitematic.com/ 
   or Boot2Docker:https://github.com/boot2docker/boot2docker
Linux - yum install docker-engine - apt-get install docker.io
Windows - Boot2Docker: https://github.com/boot2docker/boot2docker
--newpage
--heading Docker Basics
--boldon
Dockerfile - Images are built using a text file with basic instructions on how to build the docker image.
--boldoff
Command Format
--beginoutput
--color green
#comment
--color red
INSTRUCTION arguments
--color white
--endoutput
---

Commands:
--beginoutput
--color green
#what is the single upstream image to start from. See hub.docker.com
--color red
FROM <image>:<tag>
--color white
--endoutput
---

--beginoutput
--color green
#Who maintains this Docker file
--color red
MAINTAINER <name>
--color white
--endoutput
--newpage

--beginoutput
--color green
#Run a shell command in the image
--color red
RUN <command>
RUN ["executable","param1","param2"] 
--color white
--endoutput
---

--beginoutput
--color green
#ADD files from content directory, URL or compressed file
--color red
ADD <src>... <dest>
--color white
--endoutput
---

--beginoutput
--color green
#Single default command to run when image is executed
--color red
CMD <command>
CMD ["executable","param1","param2"]
--color white
--endoutput
--newpage
--heading Other Dockerfile commands:
COPY - copy files into an image
ENTRYPOINT - define command to run when executed.
VOLUME - mount a device or directory into the image
USER - what user id to execute as
WORKDIR - what directory in the image to execute in
ENV - specify environment variables
EXPOSE - allow network traffic into the image

--newpage
--heading Simple Dockerfile
--beginoutput
--color yellow
FROM karcaw/nwperf

MAINTAINER Evan Felix

CMD  nwperf-nsq.py tcp://nwperf-ns:6967 listServices
--color white
--endoutput
--newpage
--huge DEMO
Show building image, then run the image.
--beginoutput
$ docker build -t nsq .
$ docker run nsq
--endoutput
---
--exec script  -c "screen -x" /dev/null

--newpage
--huge Docker Hub

https://registry.hub.docker.com/

https://registry.hub.docker.com/u/karcaw/
--newpage
--heading Image Dependencies
--beginoutput
+---------------+     +---------------------+ 
| karcaw/nwperf | --> | karcaw/nwperf-slurm | 
+---------------+     +---------------------+ 
  |
  |
  v
+---------------+     +---------------------+
|  nwperf-auth  | --> |     nwperf-wsgi     |
+---------------+     +---------------------+
--endoutput

--newpage
--heading NWperf Dockerfile(Public)
https://github.com/EMSL-MSC/NWPerf/
--beginoutput
FROM ubuntu:trusty

MAINTAINER karcaw@gmail.com

RUN apt-get update
RUN apt-get install -y eatmydata python python-zmq python-ceph python-simplejson python-numpy

ENV PATH /bin:/sbin:/usr/bin:/usr/sbin:/app/bin:/app/sbin/
ENV PYTHONPATH /app/lib

ADD . /app
ADD conf/nwperf.conf /etc/
--endoutput
--newpage
--heading NWperf auth Dockerfile(Private)
--beginoutput
FROM karcaw/nwperf

MAINTAINER karcaw@gmail.com

RUN mkdir /etc/ceph
ADD ceph.conf  /etc/ceph/ceph.conf
ADD keyring.bin /etc/ceph/keyring.bin
RUN cat /etc/ceph/keyring.bin >> /etc/ceph/ceph.conf
--endoutput

--newpage
--huge DEMO
Show Docker Image list
--beginoutput
$ docker images
--endoutput
Show Running containers
--beginoutput
$ docker ps
--endoutput
---
--exec script  -c "screen -x" /dev/null

--newpage
--heading Dockerfile for this presentation
--beginoutput
$$ cat Dockerfile

--endoutput
--newpage
--huge Questions
