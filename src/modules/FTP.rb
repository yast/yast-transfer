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
# File:    modules/FTP.ycp
# Package: Transfer Protocols
# Summary: Handle FTP Requests
# Authors: Anas Nashif <nashif@suse.de>
# Flags:   Stable
#
# $Id$
require "yast"

module Yast
  class FTPClass < Module
    def main

      @user = ""
      @password = ""
    end

    # Send a get request
    # @param [String] url url in any standard form
    # @param [String] output file to save result to
    # @return [Hash] Reponse map with HTTP code and transfer size and time
    def Get(url, output)
      Builtins.y2debug("URL: %1", url)
      response = Convert.to_map(
        SCR.Execute(path(".curl.get"), url, { "output" => output })
      )
      deep_copy(response)
    end

    # List FTP directory
    def Dir(url)
      dir = Convert.to_map(SCR.Execute(path(".curl.ftp.dir"), url, {}))
      Builtins.y2debug("returned string: %1", dir)

      if Ops.less_or_equal(Builtins.size(dir), 0)
        Builtins.y2error("Error while trying to list directory")
        return []
      end

      Builtins.filter(
        Builtins.toset(
          Builtins.splitstring(Ops.get_string(dir, "output", ""), "\r\n")
        )
      ) { |s| s != "." && s != ".." && s != "" }
    end

    publish :variable => :user, :type => "string"
    publish :variable => :password, :type => "string"
    publish :function => :Get, :type => "map (string, string)"
    publish :function => :Dir, :type => "list (string)"
  end

  FTP = FTPClass.new
  FTP.main
end
