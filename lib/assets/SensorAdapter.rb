require 'rubygems'
require 'httparty'
require 'cgi'
require 'uri'

class SensorAdapter
  include HTTParty
  @authResults = nil
  @refreshResults = nil
  
  format :json

  #authenticate to force.com
  def self.authenticate

    base_uri = ENV['SALESFORCE_OAUTH2_URI']
    if base_uri == nil
      puts "You need to add the variables (
      SALESFORCE_OAUTH2_URI,
      SALESFORCE_OAUTH2_KEY,
      SALESFORCE_OAUTH2_SECRET,
      SALESFORCE_OAUTH2_URI,
      SALESFORCE_OAUTH2_PASSWORD
      ) to the environment."
    end
    base_auth_query = 
      'grant_type=password'+
      '&client_id='+ENV['SALESFORCE_OAUTH2_KEY']+
      '&client_secret='+ENV['SALESFORCE_OAUTH2_SECRET']+
      '&username='+ENV['SALESFORCE_OAUTH2_USERNAME']+
      '&password='+ENV['SALESFORCE_OAUTH2_PASSWORD']
    @authResults = post(base_uri, { :body => base_auth_query })
    puts @authResults.to_yaml
    
    return @authResults
  end
  
  # simply prepares the headers for a request
  def self.prepare_header(query)
    oauth_header = 'OAuth ' + @authResults['access_token']  
    headers 'Authorization' => oauth_header
    headers 'Content-Type' => 'application/json'
    return @authResults['instance_url'] + query     
  end  

  # wrapper for get
  def self.api_query(query)
    return send_query(query, "get", 0)
  end

  #wrapper for post
  def self.post_query(query)
    return send_query(query, "post", 0)    
  end
  
  ###################################################
  # Send a query to force.com
  #
  # => query  Query string URL
  # => method Method for query type {get, post}
  # => try    Number of attempts to make
  #
  # => Returns the query results as a json document 
  ###################################################
  def self.send_query(query, method, try)
    if !@authResults
      SensorAdapter.authenticate
    end

    reading_uri = prepare_header(query)
    
    if method.eql?("post")
      ret = post(reading_uri)
    else
      ret = get(reading_uri)
    end
      
    if ret.include? 'errorCode'
      if try == 0
        SensorAdapter.authenticate
        send_query(query, 1)
      else
        puts "ERROR MAKING QUERY"
        puts ret.to_yaml
      end
    end
    
    return ret    
  end
end