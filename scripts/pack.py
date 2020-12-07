import sqlite3
import os
import re
import json


def all_files(d: str, ignore=None):
    rv = list()

    offset = len(os.path.dirname(d))

    for root, subdirs, files in os.walk(d):
        root = root[offset:]
        root = root.lstrip('/')
        files = [f'{root}/{f}' for f in files]
        if ignore:
            files = [f for f in files if not ignore.match(f)]
        rv.extend(files)

    return rv


def pack_assets(assets_dir='assets', db_path='geas_files.db'):
    ase_json_undo = re.compile('.*\\.aseprite|.*~|.*\\.json')
    asset_paths = all_files(assets_dir, ignore = ase_json_undo)

    if os.path.exists(db_path):
        os.remove(db_path)

    with sqlite3.connect(db_path) as conn:
        cursor = conn.cursor()
        cursor.execute('CREATE TABLE Resources (ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, Path TEXT NOT NULL UNIQUE, Data BLOB NOT NULL, MetaData TEXT);')
        cmd = 'INSERT INTO Resources (Path,Data,MetaData) VALUES (?,?,?);'
        cmd_nometa = 'INSERT INTO Resources (Path,Data) VALUES (?,?);'

        for asset_path in asset_paths:
            meta_path = asset_path+'.json'
            meta = None
            if os.path.exists(meta_path):
                with open(meta_path, 'r') as f:
                    meta_json = json.load(f)
                meta = json.dumps(meta_json, separators=(',',':'), indent=None)

            with open(asset_path, 'rb') as f:
                asset = f.read()

            if meta:
                cursor.execute(cmd, (asset_path,asset, meta))
                print(f'Packed "{asset_path}" with its meta data.')
            else:
                cursor.execute(cmd_nometa, (asset_path,asset))
                print(f'Packed "{asset_path}".')



if __name__ == '__main__':
    pack_assets()
