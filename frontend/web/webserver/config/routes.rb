Rails.application.routes.draw do
  get 'overview/update'
  root 'location#list'

  get 'graph/list'
  get 'overview/list'
  post 'overview/update'
  get 'settings/edit'
  post 'settings/update'

  get 'device/list'
  get 'location/list'
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
