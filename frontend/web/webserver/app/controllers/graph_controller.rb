include JsonHelper
include OverviewHelper
class GraphController < ApplicationController

=begin def update
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
=end

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
      response = getJsonForType({:type => "ListData",
                    "devices" => @ids,
                    "start" => @startTime,
                    "end" => @endTime})
    rescue Errno::EHOSTUNREACH
      redirect_to settings_edit_path
      return
    end

    if response["type"] != "ListData"
      raise "Wrong return type"
    else
      @dataEntries = response["data"]
      @dataEntries.each do |device|
        transDate = []
        device["loadedTimes"].each do |entry|
          transDate.push([toTimeString(entry[0]), toTimeString(entry[1])])
        end
        device["loadedTimes"] = transDate
        transDate = []
        device["emptyTimes"].each do |entry|
          transDate.push([toTimeString(entry[0]), toTimeString(entry[1])])
        end
        device["emptyTimes"] = transDate
      end
    end
=begin
    @dataEntries = [{
            "id" => "00112233",
            "name" => "stapler1",
            "location" => "Tisch 2",
            "loadedTimes" => [["1801, 2, 4, 12, 10, 00", "1801, 2, 4, 12, 15, 00"]],
            "emptyTimes" => [["1801, 2, 4, 14, 10, 00", "1801, 2, 4, 14, 15, 00"]]
        }]
=end
  end

  def toTimeString(unformatted) 
    return unformatted.gsub(/[-T:]/, ", ")[0,24]
  end

end
