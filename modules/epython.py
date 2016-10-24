#!/usr/bin/python
import os

toepython_pipe_name="toepython"
fromepython_pipe_name="fromepython"

def sendrecv(data, pid):
	command_to_send="8 "+str(pid)+" "
	if type(data) is int:
		command_to_send+="0 "
	elif type(data) is float:
		command_to_send+="1 "
	elif type(data) is bool:
		command_to_send+="3 "
	command_to_send+="0 "+str(data)
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
	os.write(wp, command_to_send)
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	items = recv_data.split(" ")	
        if items[0]=="0":
		return int(items[2])
	if items[0]=="1":
		return float(items[2])
	if items[0]=="3":
		return bool(items[2])

def send(data, pid):	
	command_to_send="1 "+str(pid)+" "
	if type(data) is int:
		command_to_send+="0 "
	elif type(data) is float:
		command_to_send+="1 "
	elif type(data) is bool:
		command_to_send+="3 "
	command_to_send+="0 "+str(data)
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
	os.write(wp, command_to_send)
	os.close(wp)

def recv(pid):
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
	os.write(wp, "2 "+str(pid))
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	items = recv_data.split(" ")	
        if items[0]=="0":
		return int(items[2])
	if items[0]=="1":
		return float(items[2])
	if items[0]=="3":
		return bool(items[2])

def reduce(data, operator):
	command_to_send="6 "
	if operator=="sum":
		command_to_send+="0 "
	elif operator=="min":
		command_to_send+="1 "
	elif operator=="max":
		command_to_send+="2 "
	elif operator=="prod":
		command_to_send+="3 "
	else:
		print "Operator "+operator+" not found"
	
	if type(data) is int:
		command_to_send+="0 "
	elif type(data) is float:
		command_to_send+="1 "
	elif type(data) is bool:
		command_to_send+="3 "
	command_to_send+="0 "+str(data)
	
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
	os.write(wp, command_to_send)
	os.close(wp)
	
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	items = recv_data.split(" ")	
        if items[0]=="0":
		return int(items[2])
	if items[0]=="1":
		return float(items[2])
	if items[0]=="3":
		return bool(items[2])

def bcast(data, root):
	command_to_send="7 "+str(root)
	
	if type(data) is int:
		command_to_send+=" 0 "
	elif type(data) is float:
		command_to_send+=" 1 "
	elif type(data) is bool:
		command_to_send+=" 3 "
	command_to_send+="0 "+str(data)
	
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
	os.write(wp, command_to_send)
	os.close(wp)
	
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	items = recv_data.split(" ")	
        if items[0]=="0":
		return int(items[2])
	if items[0]=="1":
		return float(items[2])
	if items[0]=="3":
		return bool(items[2])

def numcores():
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
	os.write(wp, "3 ")
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	return int(recv_data)

def coreid():
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
	os.write(wp, "4 ")
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)
	return int(recv_data)

def sync():
	wp=os.open(toepython_pipe_name, os.O_NONBLOCK | os.O_WRONLY)
	os.write(wp, "5 ")
	os.close(wp)
	rp = os.open(fromepython_pipe_name, os.O_RDONLY)
	recv_data=os.read(rp, 1024)
	os.close(rp)

def ishost():
		return true

def isdevice():
		return false
