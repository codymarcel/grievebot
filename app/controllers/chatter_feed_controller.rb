require './lib/assets/SensorAdapter'
require 'json'

class ChatterFeedController < ApplicationController
  
  def index
    puts "Inside index"
  end
  
  def get_chatter_feed()
    
    puts "Getting chatter feed now bish!"
    #    client = Databasedotcom::Client.new("config/databasedotcom.yml")
    #    client.authenticate :username => "grievebot@grieve.com", :password => "gr13v3b0tMIIEijCCA/OgAwIBAgIQPn+ClEjH2V3Jynt7u3v+XzANBgkqhkiG9w0BAQUFADCBujEfMB0GA1UEChMWVmVyaVNpZ24gVHJ1c3QgTmV0d29yazEXMBUGA1UECxMOVmVyaVNpZ24sIEluYy4xMzAxBgNVBAsTKlZlcmlTaWduIEludGVybmF0aW9uYWwgU2VydmVyIENBIC0gQ2xhc3MgMzFJMEcGA1UECxNAd3d3LnZlcmlzaWduLmNvbS9DUFMgSW5jb3JwLmJ5IFJlZi4gTElBQklMSVRZIExURC4oYyk5NyBWZXJpU2lnbjAeFw0xMDEyMTQwMDAwMDBaFw0xMjAxMDcyMzU5NTlaMIGOMQswCQYDVQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQGA1UEBxQNU2FuIEZyYW5jaXNjbzEdMBsGA1UEChQUU2FsZXNmb3JjZS5jb20sIEluYy4xFDASBgNVBAsUC0FwcGxpY2F0aW9uMR0wGwYDVQQDFBRwcm94eS5zYWxlc2ZvcmNlLmNvbTCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAzKElluHQYlUnFm156Nwup9vqkf9DvnhOJc09GNYKOdz5PkpJ/bFLuN2frmfJTlw6pi4knE2geN3j26iAFGIpqgkfWmAi5knjcIbOvHbMXMg1apuVyK9jmbKy4pITZCj56PtH7qMjlmwN+ZEcQRVy+urRGJRfBEyE+ht5KrewhlcCAwEAAaOCAbkwggG1MAkGA1UdEwQCMAAwCwYDVR0PBAQDAgWgMDwGA1UdHwQ1MDMwMaAvoC2GK2h0dHA6Ly9TVlJJbnRsLWNybC52ZXJpc2lnbi5jb20vU1ZSSW50bC5jcmwwRAYDVR0gBD0wOzA5BgtghkgBhvhFAQcXAzAqMCgGCCsGAQUFBwIBFhxodHRwczovL3d3dy52ZXJpc2lnbi5jb20vcnBhMDQGA1UdJQQtMCsGCWCGSAGG+EIEAQYKKwYBBAGCNwoDAwYIKwYBBQUHAwEGCCsGAQUFBwMCMHEGCCsGAQUFBwEBBGUwYzAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AudmVyaXNpZ24uY29tMDsGCCsGAQUFBzAChi9odHRwOi8vU1ZSSW50bC1haWEudmVyaXNpZ24uY29tL1NWUkludGwtYWlhLmNlcjBuBggrBgEFBQcBDARiMGChXqBcMFowWDBWFglpbWFnZS9naWYwITAfMAcGBSsOAwIaBBRLa7kolgYMu9BSOJsprEsHiyEFGDAmFiRodHRwOi8vbG9nby52ZXJpc2lnbi5jb20vdnNsb2dvMS5naWYwDQYJKoZIhvcNAQEFBQADgYEAHP9jTz8c1r9YoOhVxbGwdPx/YU4OaEaiJFqRKrdXu4m6tHp2iW7o/7Kc8IxksDB4siloTOcJ25/NsfPRoWDyvwax0aXDzsBRwJ5Qpr+ii3bUI1+QByEdxH4gZVHHu9fMG/+ePr9SHhil20oycE7oe0xvQEad1Hs6xHCRDbJVIr4="
    #    puts client.list_sobjects
    
    feed = feed_query("feeds/groups/me/feed-items")
    
    puts feed.inspect
    @output = feed
  end

  def feed_query(query)
   return SensorAdapter.api_query('/services/data/v23.0/chatter/' + query)
  end

  def after_sign_in_path_for(user)
    #"/index.html"
  end
end
