module LocationHelper
  def getNumberOfDevices
    uri = URI.parse(Rails.configuration.jsonUri)
    header = {'Content-Type': 'text/json'}
    http = Net::HTTP.new(uri.host, uri.port)
    request = Net::HTTP::Post.new(uri.request_uri, header)
    request.body = {:type => "ListDevices",
                    "start" => nil,
                    "end" => nil,
                    "location" => nil}.to_json
    response = http.request(request)
    raise "response code != 200" if response.code != "200"
    response = JSON.parse(response.body)
    # raise "response invalid" if response[:type] != "ListDevices"
    # TODO: uncomment, if implemented
    
    if response[:type] != "ListDevices"
      devices = [{:id => 0, :name => "Stapler 1", :location => "Tisch 11"}]
    else
      devices = response["data"]
    end



    result = Hash.new(0)
    devices.each do |device|
      result[device[:location]] += 1
    end
    return result;
  end
end
