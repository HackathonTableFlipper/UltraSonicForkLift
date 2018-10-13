require 'test_helper'

class GraphControllerTest < ActionDispatch::IntegrationTest
  test "should get list" do
    get graph_list_url
    assert_response :success
  end

end
