require './lib/assets/SensorAdapter'
require './lib/assets/ResponseFilter'
require 'json'

class ChatterFeedController < ApplicationController
  @last_post_url = "none"
  @isLiked = "none"
  @error = false

  def index
    puts "Inside index"
  end
  
  ##############################################################
  # This method will Like the last comment on the chatter group
  ##############################################################
  def post_like()
    puts "Last post url: ", @_params["last_post_url"]
#    url = SensorAdapter.getUrl() + "/likes"
    url = @_params["last_post_url"] + "/likes"
    puts url
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
    @error = false
    @output = feed
    if @output.include?('items')
      @last_post_url = @output['items'][0]["url"]
      SensorAdapter.saveUrl(@last_post_url);
      @is_liked = @output['items'][0]["isLikedByCurrentUser"]
    else
      @error = true
      @last_post_url = nil
      @is_liked = nil
   end
    
    if not @error
      @bot_response = ResponseFilter.new(feed).to_xml
    else
      puts "REQUEST ERROR"
      @bot_response = feed.to_yaml
    end
    puts @bot_response
    
#    puts "Is currently like by bot: " + @is_liked.to_s
    return feed
  end

  def feed_query(query)
   return SensorAdapter.api_query(query)
  end

end
