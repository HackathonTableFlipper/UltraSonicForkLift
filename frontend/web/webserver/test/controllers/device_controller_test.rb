require 'test_helper'

class DeviceControllerTest < ActionDispatch::IntegrationTest
  test "should get list" do
    get device_list_url
    assert_response :success
  end

end
