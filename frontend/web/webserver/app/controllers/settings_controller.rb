class SettingsController < ApplicationController
  def edit
    @jsonServerUri = Rails.configuration.jsonUri;
  end

  def update
    Rails.configuration.jsonUri = params[:jsonServerUri]
    redirect_to location_list_path
  end
end
