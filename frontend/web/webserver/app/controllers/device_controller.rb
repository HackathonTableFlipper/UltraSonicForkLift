class DeviceController < ApplicationController
  include JsonHelper

  def list
    begin
      response = getJsonForType({:type => "ListDevices",
                    "start" => nil,
                    "end" => nil,
                    "location" => nil})
      puts response
    rescue Errno::EHOSTUNREACH
      redirect_to settings_edit_path
      return
    end

    if response["type"] != "ListDevices"
      raise "ListDevices response type was " + response["type"]
    else
      @devices = response["data"]
    end

  end
end
