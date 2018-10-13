class OverviewController < ApplicationController
  include JsonHelper

  def list
    @ids = params[:ids]
    @startTime = params[:ids]
    @endTime = params[:endTime]

    begin
      response = getJsonForType({:type => "ListOverview",
                    "devices" => @ids,
                    "start" => @startTime,
                    "end" => @endTime})
    rescue Errno::EHOSTUNREACH
      redirect_to settings_edit_path
      return
    end

    if response[:type] != "ListOverview"
      @overviewEntries = [{:id => "deadbeef", :name => "Stapler 1", :location => "Tisch 11", :loadedTime => 42, :emptyTime => 24}]
    else
      @overviewEntries = response["data"]
    end
    @overviewEntries.each do |entry|
    entry[:time] = entry[:emptyTime] + entry[:loadedTime]
    entry[:percentage] = entry[:loadedTime] * 100 / entry[:time]
  end

  end
end
