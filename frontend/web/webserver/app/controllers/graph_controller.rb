class GraphController < ApplicationController
  include GraphHelper

  def list
    @graphEntries = [[34, 42], [56, 49]]
  end
end
