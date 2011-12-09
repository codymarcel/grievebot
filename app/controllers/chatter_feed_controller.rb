class ChatterFeedController < ApplicationController
  def index
    puts "Inside index"    
  end

  def get_chatter_feed()
    foo = "foo"
    puts "Getting chatter feed "
    
  end
  
  def after_sign_in_path_for(user)
    #"/index.html"
  end
end
