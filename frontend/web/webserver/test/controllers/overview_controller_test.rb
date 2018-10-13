require 'test_helper'

class OverviewControllerTest < ActionDispatch::IntegrationTest
  test "should get list" do
    get overview_list_url
    assert_response :success
  end

end
