class StaticMessageController < ApplicationController
  def index
  end
  
  def get_message
    controller.request.env.each do |header|
       log_detail = LogDetail.new
       log_detail.log_id = log.id
       log_detail.detail_key    = header[0]
       log_detail.detail_value  = header[1]
       log_detail.save
    end
    
    @feed = "Ownage!"
    puts @feed
    @message = @feed
  end
  
  
end
