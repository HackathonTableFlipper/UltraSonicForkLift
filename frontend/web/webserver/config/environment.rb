# Load the Rails application.
require_relative 'application'

Rails.configuration.jsonUri = "http://172.16.7.71:8080/"

# Initialize the Rails application.
Rails.application.initialize!
