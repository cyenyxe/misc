#!/bin/python

import argparse
import gzip
from itertools import islice
import json
import sys
from pymongo import Connection


def build_cli_arguments():
  parser = argparse.ArgumentParser(description="Insert a JSON file into a Mongo collection");
  
  parser.add_argument("--host", action="store", dest="host", help="Database host");
  parser.add_argument("-P", "--port", action="store", dest="port", type=int, help="Database port");
  parser.add_argument("-d", "--database", action="store", dest="database", help="Database name", required=True);
  parser.add_argument("-u", "--user", action="store", dest="user", help="Database user name");
  parser.add_argument("-p", "--password", action="store", dest="password", help="Database user password");
  
  parser.add_argument("-f", "--file", action="store", dest="file", help="File to save into the database", required=True);
  parser.add_argument("-c", "--collection", action="store", dest="collection", help="Collection to save the information to", required=True);
  
  parser.add_argument("-b", "--batch-size", action="store", dest="batch_size", type=int, help="Number of lines to process in each step");
  parser.add_argument("-w", "--write-concern", action="store", dest="write_concern", help="MongoDB write concern");

  parser.set_defaults(host="localhost");
  parser.set_defaults(port=27017);
  parser.set_defaults(user="anonymous");
  
  parser.set_defaults(batch_size=1000);
  parser.set_defaults(write_concern="journaled");
  
  return parser


def process_loop(f, n):
  while True:
    next_n_lines = list(islice(f, n))
    
    if not next_n_lines:
	break
    
    # Convert next_n_lines from JSON
    loaded_data = []
    #load_json(next_n_lines)
    for line in next_n_lines:
      loaded_data.append(load_json(line))
      
    # Write lines to Mongo
    if len(save_to_mongo(loaded_data, coll)) < n:
      print("Error while storing data in collection")
      print(loaded_data)
      break
        

def load_json(data):
  return json.loads(data)


def save_to_mongo(data, collection):
  return collection.insert(data)


#
# Program entry point
#
if __name__ == "__main__":
  # Parse CLI arguments
  cli_parser = build_cli_arguments()
  args = cli_parser.parse_args()
  filename = args.file
  
  # Create DB connection
  mongo = Connection(args.host, args.port)
  db = mongo[args.database]
  coll = db[args.collection]

  # Use one file loader or another depending of its extension
  if filename.endswith(".gz"):
    with gzip.open(filename) as f:
      process_loop(f, args.batch_size)
  else:
    with open(filename) as f:
      process_loop(f, args.batch_size)
        
  mongo.disconnect()
  
