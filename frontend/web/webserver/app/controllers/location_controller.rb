require "rubygems"
require "json"
require "net/http"
require "uri"

class LocationController < ApplicationController
  include LocationHelper

  def list
    uri = URI.parse("http://172.16.7.71:8080/")
    header = {'Content-Type': 'text/json'}
    http = Net::HTTP.new(uri.host, uri.port)
    request = Net::HTTP::Post.new(uri.request_uri, header)
    request.body = {:type => "ListLocations"}.to_json
    response = http.request(request)
    raise "response code != 200" if response.code != "200"
    response = JSON.parse(response.body)
    raise "invalid response" if response["type"] != "ListLocations"
    @locations = response["data"]

    @devicesPerLocation = getNumberOfDevices()
  end
end
