#!/usr/bin/env python
import os
import pwd
import commands
import re

#
# Utility to find out if you have an ssh-agent running that is holding your
# private key.  To use this in bash:
#
#     eval $(python ./setSetSshEnv.python)
#
# It assumes that ssh creates files of the form /tmp/ssh-Abcdefg12345/agent.12345 .
#
# TODO 1: It would be better to skip the socket query and instead look directly for the ssh-agent lock files.
# Fingerprint of identity that you will use. You can find it with "ssh-add -l".
keyFingerprint = "4096 bf:65:91:4a:0a:01:e9:72:fe:73:b6:9d:15:f5:cb:f4 /home/aprokop/.ssh/id_rsa (RSA)"

# socket query tool
socketCommand = "/usr/sbin/ss"

# Your username.
userid = pwd.getpwuid(os.getuid())[0]

[status,charlist] = commands.getstatusoutput(socketCommand + " -xl | grep -o '/tmp/ssh-[[:alnum:]]*/agent.[[:digit:]]*'")
# convert raw characters into list
agentList = [s.strip() for s in charlist.splitlines()]
keyFound  = 0
for agent in agentList:
  # See if this is your agent by checking ownership of root of lock directory
  # Check only the root, because if it's not yours, you can't see down into it.
  pieces   = agent.split("/")
  rootDir  = "/" + pieces[1] + "/" + pieces[2]
  st       = os.stat(rootDir)
  dirOwner = pwd.getpwuid(st.st_uid).pw_name

  if dirOwner == userid:
    # Your ssh agent has been found
    sshAgentCmd = "SSH_AUTH_SOCK=" + agent + " ssh-add -l"
    [status,result] = commands.getstatusoutput(sshAgentCmd)
    keyList = [s.strip() for s in result.splitlines()]

    # Check whether this key's fingerprint matches the desired key's
    for key in keyList:
      if key == keyFingerprint:
        keyFound = 1
        print "export SSH_AUTH_SOCK=" + agent
        break

# if no key matches, just use the last agent found
if keyFound == 0:
  print "export SSH_AUTH_SOCK=" + agent
