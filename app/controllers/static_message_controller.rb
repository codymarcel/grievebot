class StaticMessageController < ApplicationController
  def index
  end
  
  def get_message    
    @feed = "Ownage!"
    puts @feed
    @message = @feed
  end
    
end
