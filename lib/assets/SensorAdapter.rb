require 'rubygems'
require 'httparty'
require 'cgi'

class SensorAdapter
  include HTTParty
  @@authResults = nil
  
  format :json

  #authenticate
  def self.authenticate
    base_uri = ENV['SALESFORCE_OAUTH2_URI']
    base_auth_query = 'grant_type=password&client_id='+ENV['SALESFORCE_OAUTH2_KEY']+
      '&client_secret='+ENV['SALESFORCE_OAUTH2_SECRET']+
      '&username='+ENV['SALESFORCE_OAUTH2_USERNAME']+
      '&password='+ENV['SALESFORCE_OAUTH2_PASSWORD']
    puts base_auth_query.to_yaml
    @@authResults = post(base_uri, { :body => base_auth_query })
    puts @@authResults.to_yaml
    return @@authResults
  end

  def self.api_query(query_stuff)
    if !@@authResults
      SensorAdapter.authenticate
    end
   
    headers 'Authorization' => 'OAuth ' + @@authResults["access_token"]
    headers 'Content-Type' => 'application/json'
    reading_uri = @@authResults["instance_url"] + '/services/data/v23.0/' + query_stuff
    
    puts "Querying: " + reading_uri
    
    ret = HTTParty.get(reading_uri)
    
    return ret
    
  end

end