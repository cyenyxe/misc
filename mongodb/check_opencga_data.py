import argparse
from pymongo import MongoClient 

def build_cli_arguments():
  parser = argparse.ArgumentParser(description="Verify an OpenCGA-based variant database");
  
  parser.add_argument("--host", action="store", dest="host", help="Database host");
  parser.add_argument("-P", "--port", action="store", dest="port", type=int, help="Database port");
  parser.add_argument("-d", "--database", action="store", dest="database", help="Database name", required=True);
  parser.add_argument("-u", "--user", action="store", dest="user", help="Database user name");
  parser.add_argument("-p", "--password", action="store", dest="password", help="Database user password");

  parser.add_argument("-f", "--collection-files", action="store", dest="collection_files", help="Collection containing the files information", required=True);
  parser.add_argument("-v", "--collection-variants", action="store", dest="collection_variants", help="Collection containing the variants information", required=True);

  parser.set_defaults(host="localhost");
  parser.set_defaults(port=27017);
  parser.set_defaults(user="anonymous");
  parser.set_defaults(collection_files="files");
  parser.set_defaults(collection_variants="variants");

  return parser 


def check_files(collection):
  """
  Retrieves information from the collection storing files metadata.
  - Total number of files
  - Number of files per study
  - Created indexes
  """
  print("Collection '" + collection.name + "'")
  
  count = collection.count()
  print("No. files: {0}".format(count))

  count_per_study = collection.aggregate([
      { '$project' : { '_id' : 0, 'sid' : 1, 'sname' : 1 } },
      { '$group' : { 
        '_id' : { 'study id' : "$sid", 'study name' : "$sname" },
        'num sources' : { '$sum' : 1 }
        }
      }
    ])
  print("No. files per study:")
  for c in count_per_study['result']:
    print("{0} - {1} files \t({2})".format(c['_id']['study id'], c['num sources'], c['_id']['study name']))

  indexes = collection.index_information()
  print("No. indexes: {0}".format(len(indexes)))
  print("Indexes: {0}".format(indexes.keys()))



def check_variants(collection):
  """
  Retrieves information from the collection storing variants data.
  - Total number of variants 
  - Created indexes
  """
  print("Collection '" + collection.name + "'")

  count = collection.count()
  print("No. variants: {0}".format(count))

#  count_per_chr = collection.aggregate([
#      { '$project' : { '_id' : 0, 'chr' : 1 } },                               
#      { '$group' : { 
#        '_id' : { 'chromosome' : "$chr" },
#        'num variants' : { '$sum' : 1 }
#        }
#      }
#    ])
#  print("No. variants per chromosome:")
#  for c in count_per_study['result']:
#    print("{0} - {1} variants".format(c['_id']['chromosome'], c['num variants']))
  
  indexes = collection.index_information()
  print("No. indexes: {0}".format(len(indexes)))
  print("Indexes: {0}".format(indexes.keys()))


#
# Program entry point
#
if __name__ == "__main__":
  # Parse CLI arguments
  cli_parser = build_cli_arguments()
  args = cli_parser.parse_args()
  
  # Create DB connection
  mongo = MongoClient(args.host, args.port)
  db = mongo[args.database]
  db.authenticate(args.user, args.password)

  print("Checking information in database '" + args.database + "'...\n")
  check_files(db[args.collection_files])
  print("")
  check_variants(db[args.collection_variants])

  mongo.disconnect()

