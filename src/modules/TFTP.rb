# encoding: utf-8

# ***************************************************************************
#
# Copyright (c) 2000 - 2012 Novell, Inc.
# All Rights Reserved.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of version 2 of the GNU General Public License as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, contact Novell, Inc.
#
# To contact Novell about this file by physical or electronic mail,
# you may find current contact information at www.novell.com
#
# ***************************************************************************
# File:    modules/TFTP.ycp
# Package: Transfer Protocols
# Summary: Handle TFTP Requests
# Authors: Anas Nashif <nashif@suse.de>
# Flags:   Stable
#
# $Id$
#
require "yast"

module Yast
  class TFTPClass < Module
    def main

    end

    # Send a get request
    # @param [String] server server address
    # @param [String] remote  remote file
    # @param [String] local file to save result to
    # @return [Boolean] true on success
    def Get(server, remote, local)
      serverstr = Builtins.sformat("%1:%2", server, remote)
      Convert.to_boolean(SCR.Execute(path(".tftp.get"), serverstr, local))
    end

    # Send a put request
    # @param [String] server server address
    # @param [String] remote  remote file
    # @param [String] local file to save result to
    # @return [Boolean] true on success
    def Put(server, remote, local)
      serverstr = Builtins.sformat("%1:%2", server, remote)
      Convert.to_boolean(SCR.Execute(path(".tftp.put"), serverstr, local))
    end

    publish :function => :Get, :type => "boolean (string, string, string)"
    publish :function => :Put, :type => "boolean (string, string, string)"
  end

  TFTP = TFTPClass.new
  TFTP.main
end
