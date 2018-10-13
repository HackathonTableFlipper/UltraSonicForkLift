require 'net/http'

module JsonHelper
  def getJsonForType(requestMessage)
    uri = URI.parse(Rails.configuration.jsonUri)
    header = {'Content-Type': 'text/json'}
    http = Net::HTTP.new(uri.host, uri.port)
    request = Net::HTTP::Post.new(uri.request_uri, header)
    request.body = requestMessage.to_json
    response = http.request(request)
    raise "response code != 200" if response.code != "200"
    return JSON.parse(response.body)
  end
end
