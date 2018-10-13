module LocationHelper
  def getNumberOfDevices
    response = getJsonForType({"type" => "ListDevices",
                    "start" => nil,
                    "end" => nil,
                    "location" => nil})
    if response["type"] != "ListDevices"
      raise "Wrong List type"
    else
      devices = response["data"]
    end

    result = Hash.new(0)
    devices.each do |device|
      result[device["location"]] += 1
    end
    return result;
  end
end
