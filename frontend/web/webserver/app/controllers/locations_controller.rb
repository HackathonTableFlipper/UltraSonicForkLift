require "rubygems"
require "json"
require "net/http"
require "uri"

class LocationsController < ApplicationController

  def list
    uri = URI.parse("http://172.16.7.71:8080/")
    http = Net::HTTP.new(uri.host, uri.port)
    request = Net::HTTP::Get.new(uri.request_uri)
    response = http.request(request)
    if response.code == "200"
		@locations = JSON.parse(response.body)["data"]
    else
      response.inspect
    end
  end
end
