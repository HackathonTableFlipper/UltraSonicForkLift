ENV['BUNDLE_GEMFILE'] ||= File.expand_path('../Gemfile', __dir__)

require 'bundler/setup' # Set up gems listed in the Gemfile.
# require 'bootsnap/setup' # Speed up boot time by caching expensive operations.
# don't use bootsnap on ARM7 processors (RPI). See: https://romkey.com/2018/05/14/fixing-rails-5-2-bus-error-on-armv7-raspberry-pi/
