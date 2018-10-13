require "rubygems"
require "json"
require "net/http"
require "uri"

class LocationController < ApplicationController
  include LocationHelper
  include JsonHelper

  def list
    begin
      response = getJsonForType({:type => "ListLocations"})
    rescue Errno::EHOSTUNREACH
      redirect_to settings_edit_path
      return
    end
    raise "invalid response" if response["type"] != "ListLocations"
    @locations = response["data"]

    @devicesPerLocation = getNumberOfDevices()
  end
end


