class OverviewController < ApplicationController
  include JsonHelper
  include OverviewHelper

  def update
      if (params["ids"] != nil)
        Rails.configuration.ids = params["ids"].split(",").map(&:strip)
      end
      Rails.configuration.startTime = params["startTime"]
      Rails.configuration.endTime = params["endTime"]
    
      redirect_to overview_list_path
      return
  end

  def list
    if (Rails.configuration.ids == nil || Rails.configuration.ids.empty?)
      @ids = getAllDevices
    else
      @ids = Rails.configuration.ids
    end
    if (Rails.configuration.startTime == nil)
      @startTime = "2018-10-13 00:00:00"
    else
      @startTime = Rails.configuration.startTime
    end
    if (Rails.configuration.endTime == nil)
      @endTime = "2999-01-01 00:00:00"
    else
      @endTime = Rails.configuration.endTime
    end
    begin
      response = {"type" => "ListOverview",
              "data" => [{"loadedTime" => 3,
              "emptyTime" => 4}]}
      response = getJsonForType({:type => "ListOverview",
                    "devices" => @ids,
                    "start" => @startTime,
                    "end" => @endTime})
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
