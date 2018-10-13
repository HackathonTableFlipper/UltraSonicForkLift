Rails.application.routes.draw do
  root 'location#list'

  get 'overview/list'
  post 'overview/list'
  get 'settings/edit'
  post 'settings/update'

  get 'device/list'
  get 'location/list'
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
