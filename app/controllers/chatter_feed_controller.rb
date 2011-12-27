require './lib/assets/SensorAdapter'
require './lib/assets/ResponseFilter'
require 'json'

class ChatterFeedController < ApplicationController
  @last_post_url = "none"
  @isLiked = "none"

  def index
    puts "Inside index"
  end
  
  ##############################################################
  # This method will Like the last comment on the chatter group
  ##############################################################
  def post_like()
    
    url = @_params["last_post_url"] + "/likes"
    feed = SensorAdapter.post_query(url)

    redirect_to "/chatter_feed/feed"
  end
  
  ##############################################################
  # This method will retrieve the last comment on the chatter group
  #
  # => @output will     be the feed itself as a json document
  # => @last_post_url   This is the URL for the last post to the group
  ##############################################################
  def get_chatter_feed()
    
    feed = feed_query("/services/data/v23.0/chatter/feeds/groups/me/feed-items")
    
    
#    puts feed.to_xml

    @output = feed
    @last_post_url = @output['items'][0]["url"]
    @is_liked = @output['items'][0]["isLikedByCurrentUser"]
    
    @bot_response = ResponseFilter.new(feed).to_xml
    puts @bot_response
    
#    puts "Is currently like by bot: " + @is_liked.to_s
    return feed
  end

  def feed_query(query)
   return SensorAdapter.api_query(query)
  end

end
