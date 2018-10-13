class DeviceController < ApplicationController
  include JsonHelper

  def list
    begin
      response = getJsonForType({:type => "ListDevices",
                    "start" => nil,
                    "end" => nil,
                    "location" => nil})
    rescue Errno::EHOSTUNREACH
      redirect_to settings_edit_path
      return
    end

    if response[:type] != "ListDevices"
      @devices = [{:id => 0, :name => "Stapler 1", :location => "Tisch 11"}]
    else
      @devices = response["data"]
    end

  end
end
