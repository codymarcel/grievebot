class LikeController < ApplicationController
  def new
    puts "Inside new"  
    redirect_to "/like"
  end  

  def like_post    
    puts "Inside like_post"
  end
end
