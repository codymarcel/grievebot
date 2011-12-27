require './lib/assets/SensorAdapter'
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
    
    puts feed.inspect
    @output = feed
    @last_post_url = @output['items'][0]["url"]
    @isLiked = @output['items'][0]["isLikedByCurrentUser"]
    
    puts "Is currently like by bot: " + @isLiked.to_s
    return feed
  end

  def feed_query(query)
   return SensorAdapter.api_query(query)
  end

end
