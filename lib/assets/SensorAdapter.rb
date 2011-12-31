require 'rubygems'
require 'httparty'
require 'cgi'
require 'uri'

class SensorAdapter
  include HTTParty
  @authForceResults = nil
  @authDBResults = nil
  @refreshResults = nil
  
  format :json

  #################################################
  # Used for easy switch between login credentials
  #
  # target  {SALESFORCE, DBDOTCOM}
  #################################################
  def self.authenticate_force(target)
    
    if ENV['APPLY_MSG_RULES'] == nil || ENV[target.upcase + '_OAUTH2_URI'] == nil
      err_msg = "You need to add the variables (
      APPLY_MSG_RULES,"
      target.upcase + "_OAUTH2_URI,"
      target.upcase + "_OAUTH2_KEY,"
      target.upcase + "_OAUTH2_SECRET,"
      target.upcase + "_OAUTH2_URI,"
      target.upcase + "_OAUTH2_PASSWORD
      ) to the environment." 
      
      puts err_msg
      raise err_msg
    end
    base_auth_query = 
      'grant_type=password'+
      '&client_id='+ENV[target.upcase + '_OAUTH2_KEY']+
      '&client_secret='+ENV[target.upcase + '_OAUTH2_SECRET']+
      '&username='+ENV[target.upcase + '_OAUTH2_USERNAME']+
      '&password='+ENV[target.upcase + '_OAUTH2_PASSWORD']
    results = post(ENV[target.upcase + '_OAUTH2_URI'], { :body => base_auth_query })
    puts results.to_yaml
    
    return results
  end
  
  #authenticate to force.com and db.com
  def self.authenticate
    @authForceResults = authenticate_force("SALESFORCE")
    
    #Currently message rules are the only thing
    #stored in db.com.        
    if ENV['APPLY_MSG_RULES'].eql? "true"
     # @authDBResults = authenticate_force("DBDOTCOM")    
    end
  end
  
  # simply prepares the headers for a request
  def self.prepare_header(info, query)
    oauth_header = 'OAuth ' + info['access_token']  
    headers 'Authorization' => oauth_header
    headers 'Content-Type' => 'application/json'
    return info['instance_url'] + query     
  end  

  # wrapper for get
  def self.api_query(query)
    if !@authForceResults && !@authDBResults
      SensorAdapter.authenticate
    end
    return send_query(@authForceResults, query, "get", 0)
  end

  #wrapper for post
  def self.post_query(query)
    if !@authForceResults || !@authDBResults
      SensorAdapter.authenticate
    end
    return send_query(@authForceResults, query, "post", 0)    
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
  def self.send_query(info, query, method, try)

    reading_uri = prepare_header(info, query)
    
    if method.eql?("post")
      ret = post(reading_uri)
    else
      ret = get(reading_uri)
    end
      
    if ret.include? 'ErrorCode'
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