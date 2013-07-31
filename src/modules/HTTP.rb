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
# File:    modules/HTTP.ycp
# Package: Transfer Protocols
# Summary: Handle HTTP Requests
# Authors: Anas Nashif <nashif@suse.de>
# Flags:   Stable
#
# $Id$
require "yast"

module Yast
  class HTTPClass < Module
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

    # Send a post request
    # @param [String] url url in any standard form
    # @param [String] output file to save result to
    # @param postdata the rest of the url and whatever comes after the ? in the URL
    # @return [Hash] Reponse map with HTTP code and transfer size and time

    def Post(url, output, postData)
      Builtins.y2debug("URL: %1", url)
      response = Convert.to_map(
        SCR.Execute(
          path(".curl.get"),
          url,
          { "output" => output, "data" => postData }
        )
      )
      deep_copy(response)
    end


    # Set user and password for HTTP authentication


    def setUserPassword
      userpass = Builtins.sformat("%1:%2", @user, @password)
      Convert.to_map(SCR.Execute(path(".curl.setUserPassword"), userpass, {}))
    end

    def easySSL(easy)
      Builtins.y2debug("setting easySSL to %1", easy)
      SCR.Execute(path(".curl.easySSL"), easy, {})
      nil
    end

    def clientCertSSL(cert_path)
      Builtins.y2debug("setting clientCertSSL to %1", cert_path)
      SCR.Execute(path(".curl.clientCertSSL"), cert_path, {})
      nil
    end

    def clientKeySSL(key_path)
      Builtins.y2debug("setting clientKeySSL to %1", key_path)
      SCR.Execute(path(".curl.clientKeySSL"), key_path, {})
      nil
    end

    publish :variable => :user, :type => "string"
    publish :variable => :password, :type => "string"
    publish :function => :Get, :type => "map (string, string)"
    publish :function => :Post, :type => "map (string, string, string)"
    publish :function => :setUserPassword, :type => "map ()"
    publish :function => :easySSL, :type => "void (boolean)"
    publish :function => :clientCertSSL, :type => "void (string)"
    publish :function => :clientKeySSL, :type => "void (string)"
  end

  HTTP = HTTPClass.new
  HTTP.main
end
