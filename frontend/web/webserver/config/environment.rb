# Load the Rails application.
require_relative 'application'

Rails.configuration.jsonUri = "http://172.16.7.71:8080/"
Rails.configuration.ids = nil
Rails.configuration.startTime = nil
Rails.configuration.endTime = nil


# Initialize the Rails application.
Rails.application.initialize!
