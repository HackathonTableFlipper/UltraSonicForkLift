module OverviewHelper
    def getAllDevices
      response = getJsonForType({"type" => "ListDevices",
                    "start" => nil,
                    "end" => nil,
                    "location" => nil})
    if response["type"] != "ListDevices"
      raise "Wrong List type"
    else
      devices = response["data"]
    end
    return devices.map! { |device| device.first[1] }
  end

end
