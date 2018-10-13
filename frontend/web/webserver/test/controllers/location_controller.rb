require 'test_helper'

class LocationsControllerTest < ActionDispatch::IntegrationTest
  test "should get list" do
    get location_list_url
    assert_response :success
  end

end
