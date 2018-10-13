class DeviceController < ApplicationController
  def list
    uri = URI.parse(Rails.configuration.jsonUri)
    header = {'Content-Type': 'text/json'}
    http = Net::HTTP.new(uri.host, uri.port)
    request = Net::HTTP::Post.new(uri.request_uri, header)
    request.body = {:type => "ListDevices",
                    "start" => nil,
                    "end" => nil,
                    "location" => nil}.to_json
    begin
      response = http.request(request)
    rescue Exception => e
      redirect_to settings_edit_path
      return
    end
    raise "response code != 200" if response.code != "200"
    response = JSON.parse(response.body)
    # raise "response invalid" if response[:type] != "ListDevices"
    # TODO: uncomment, if implemented
    
    if response[:type] != "ListDevices"
      @devices = [{:id => 0, :name => "Stapler 1", :location => "Tisch 11"}]
    else
      @devices = response["data"]
    end
  end
end
