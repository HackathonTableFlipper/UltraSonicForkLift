class OverviewController < ApplicationController
  include JsonHelper
  include OverviewHelper

  def update
      pIds = params[:ids] 
      if (pIds != null)
          pIdList = pIds.split(",")
          pIdList.map!(&:chomp!)
          @ids = pIdList
      else
          @ids = getAllDevices
      end
      @startTime = params[:startTime] || "2018-10-13 00:00:00"
      @endTime = params[:endTime] || "2999-01-01 00:00:00"
    
      redirect_to overview_list_path
      return
  end

  def list
    begin
      puts getAllDevices()
      response = getJsonForType({:type => "ListOverview",
                    "devices" => @ids,
                    "start" => @startTime,
                    "end" => @endTime})
      puts response
    rescue Errno::EHOSTUNREACH
      redirect_to settings_edit_path
      return
    end

    if response["type"] != "ListOverview"
      raise "Wrong return type"
    else
      @overviewEntries = response["data"]
    end
    @overviewEntries.each do |entry|
    entry["time"] = entry["emptyTime"] + entry["loadedTime"]
    entry["percentage"] = entry["loadedTime"] * 100 / entry["time"]
  end

  end
end
