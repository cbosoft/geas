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

def clean_db(db_path):
    if os.path.exists(db_path):
        os.remove(db_path)

    with sqlite3.connect(db_path) as conn:
        cursor = conn.cursor()
        cursor.execute('CREATE TABLE Resources (ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, Path TEXT NOT NULL UNIQUE, Data BLOB, MetaData TEXT);')


def pack_assets(db_path):
    ase_json_undo = re.compile('.*\\.aseprite|.*~|.*\\.json')
    asset_paths = all_files('assets', ignore = ase_json_undo)

    with sqlite3.connect(db_path) as conn:
        cursor = conn.cursor()
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
                print(f'Packed asset "{asset_path}" with its meta data.')
            else:
                cursor.execute(cmd_nometa, (asset_path,asset))
                print(f'Packed asset "{asset_path}".')

def pack_rooms(db_path):
    not_json = re.compile('.*(?<!.json)$')
    room_paths = all_files('assets/rooms', ignore=not_json)

    with sqlite3.connect(db_path) as conn:
        cursor = conn.cursor()
        cmd = 'INSERT INTO Resources (Path,MetaData) VALUES (?,?);'

        for room_path in room_paths:
            room_path = f'assets/{room_path}'

            with open(room_path, 'r') as f:
                room = f.read()

            cursor.execute(cmd, (room_path, room))
            print(f'Packed room "{room_path}".')

def pack_shaders(db_path):
    undo = re.compile('.*~')
    shader_paths = all_files('shaders', ignore=undo)

    with sqlite3.connect(db_path) as conn:
        cursor = conn.cursor()
        cmd = 'INSERT INTO Resources (Path,Data) VALUES (?,?);'

        for shader_path in shader_paths:
            with open(shader_path, 'rb') as f:
                shader = f.read()

            cursor.execute(cmd, (shader_path,shader))
            print(f'Packed shader "{shader_path}".')



if __name__ == '__main__':
    db_path = 'geas_files.db'

    clean_db(db_path)
    pack_assets(db_path)
    pack_rooms(db_path)
    pack_shaders(db_path)
