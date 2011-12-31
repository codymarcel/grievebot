require 'xml'

class ResponseFilter
  attr_accessor :message
  
  def initialize(message)
    @message = message
  end
  
  def to_xml()
    output = XML::Document.new()
    output.root = XML::Node.new('response')
    
    #add author
    author = XML::Node.new('author')
    author << XML::Node.new_text(@message['items'][0]["actor"]["name"])
    output.root << author

    # add url
    last_post_url = XML::Node.new('last_post_url')
    last_post_url << XML::Node.new_text(@message['items'][0]["url"])
    output.root << last_post_url
    
    #add isLiked
    is_liked = XML::Node.new('is_liked')
    is_liked << XML::Node.new_text(@message['items'][0]["isLikedByCurrentUser"].to_s)
    output.root << is_liked
    
    #add message
    message = XML::Node.new('message')
    message << XML::Node.new_text(@message['items'][0]["body"]["text"])
    output.root << message

    return output.to_s
  end
  
  def to_json()
    return @message.to_json
  end
  
end