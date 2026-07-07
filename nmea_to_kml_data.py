#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
nmea_speed_win.py  (Windows / VS Code friendly)
-----------------------------------------------
Reads an NMEA log file (GGA sentences) and produces:
  1) A CSV table (time, lat, lon, altitude, fix, speed).
  2) A KML track colored by speed (open in Google Earth).
  3) A summary (distance, duration, average / max speed).

HOW TO RUN ON WINDOWS / VS CODE:
  - Just open this file in VS Code and press Run (the play button) or F5.
    A window will pop up; pick your .nmea file. Done.
  - Or from a terminal:  python nmea_speed_win.py myfile.nmea

No extra installation required (Python standard library only).
"""

import math
import os
import sys

# --- Settings you can tweak ---------------------------------------------------
SMOOTH_WINDOW = 1   # moving-average window for speed; 1 = no smoothing, try 5
# -----------------------------------------------------------------------------

# Speed color scale, slow -> fast (KML ABGR).
SPEED_COLORS = [
    "ff00ff00",  # green  (slowest)
    "ff00ffff",  # yellow
    "ff00a5ff",  # orange
    "ff0050ff",  # orange-red
    "ff0000ff",  # red    (fastest)
]

FIX_LABEL = {0: "No fix", 1: "GPS", 2: "DGPS", 3: "PPS",
             4: "RTK Fixed", 5: "RTK Float", 6: "Estimated"}


def validate_checksum(sentence):
    if "*" not in sentence:
        return True
    body, _, cksum = sentence.partition("*")
    cksum = cksum.strip()[:2]
    if len(cksum) < 2:
        return True
    calc = 0
    for ch in body[1:]:
        calc ^= ord(ch)
    try:
        return calc == int(cksum, 16)
    except ValueError:
        return True


def to_decimal(value, hemisphere):
    if not value:
        return None
    try:
        v = float(value)
    except ValueError:
        return None
    deg = int(v / 100)
    dec = deg + (v - deg * 100) / 60.0
    if hemisphere in ("S", "W"):
        dec = -dec
    return dec


def parse_time(s):
    if not s or len(s) < 6:
        return None
    try:
        return int(s[0:2]) * 3600 + int(s[2:4]) * 60 + float(s[4:])
    except ValueError:
        return None


def haversine(lat1, lon1, lat2, lon2):
    r = 6371000.0
    p1, p2 = math.radians(lat1), math.radians(lat2)
    dphi = math.radians(lat2 - lat1)
    dlam = math.radians(lon2 - lon1)
    a = math.sin(dphi / 2) ** 2 + math.cos(p1) * math.cos(p2) * math.sin(dlam / 2) ** 2
    return 2 * r * math.asin(math.sqrt(a))


def iter_sentences(line):
    """A log line may contain junk and several glued NMEA sentences.
    Split on '$' and yield each reconstructed candidate sentence."""
    for frag in line.split("$"):
        frag = frag.strip()
        if frag:
            yield "$" + frag


def read_points(path):
    pts = []
    with open(path, "r", encoding="utf-8", errors="ignore") as f:
        for line in f:
            for s in iter_sentences(line.strip()):
                if "GGA" not in s[:7] or not validate_checksum(s):
                    continue
                fields = s.split("*")[0].split(",")
                if len(fields) < 10:
                    continue
                lat = to_decimal(fields[2], fields[3])
                lon = to_decimal(fields[4], fields[5])
                t = parse_time(fields[1])
                if lat is None or lon is None or t is None:
                    continue
                try:
                    q = int(fields[6]) if fields[6] else 0
                except ValueError:
                    q = 0
                if q == 0:
                    continue
                try:
                    alt = float(fields[9]) if fields[9] else 0.0
                except ValueError:
                    alt = 0.0
                pts.append({"t": t, "lat": lat, "lon": lon, "alt": alt, "q": q})
    return pts


def compute_speeds(pts):
    for idx, p in enumerate(pts):
        if idx == 0:
            p["dt"] = p["dist"] = p["v"] = 0.0
            continue
        prev = pts[idx - 1]
        dt = p["t"] - prev["t"]
        if dt < 0:
            dt += 86400.0
        dist = haversine(prev["lat"], prev["lon"], p["lat"], p["lon"])
        p["dt"], p["dist"] = dt, dist
        p["v"] = (dist / dt) if dt > 0 else 0.0


def smooth_speeds(pts, window):
    if window <= 1:
        return
    raw = [p["v"] for p in pts]
    half = window // 2
    for i in range(len(pts)):
        chunk = raw[max(0, i - half):min(len(pts), i + half + 1)]
        pts[i]["v"] = sum(chunk) / len(chunk)


def write_csv(pts, path):
    with open(path, "w", encoding="utf-8", newline="") as f:
        f.write("index,utc_seconds,latitude,longitude,altitude_m,"
                "fix,dt_s,dist_m,speed_ms,speed_kmh\n")
        for i, p in enumerate(pts):
            f.write("{},{:.2f},{:.8f},{:.8f},{:.2f},{},{:.2f},{:.3f},"
                    "{:.3f},{:.2f}\n".format(
                        i, p["t"], p["lat"], p["lon"], p["alt"],
                        FIX_LABEL.get(p["q"], "?"),
                        p["dt"], p["dist"], p["v"], p["v"] * 3.6))


def speed_band(v_kmh, vmax):
    if vmax <= 0:
        return 0
    return max(0, min(len(SPEED_COLORS) - 1, int(v_kmh / vmax * len(SPEED_COLORS))))


def write_kml(pts, path, vmax_kmh):
    out = ['<?xml version="1.0" encoding="UTF-8"?>',
           '<kml xmlns="http://www.opengis.net/kml/2.2">',
           '<Document>', '  <name>Speed-colored track</name>']
    for b, color in enumerate(SPEED_COLORS):
        out.append('  <Style id="s{}"><LineStyle><color>{}</color>'
                   '<width>4</width></LineStyle></Style>'.format(b, color))
    out.append('  <Folder><name>Track by speed</name>')
    i, n = 1, len(pts)
    while i < n:
        band = speed_band(pts[i]["v"] * 3.6, vmax_kmh)
        coords = ["{:.8f},{:.8f},{:.2f}".format(
            pts[i - 1]["lon"], pts[i - 1]["lat"], pts[i - 1]["alt"])]
        while i < n and speed_band(pts[i]["v"] * 3.6, vmax_kmh) == band:
            coords.append("{:.8f},{:.8f},{:.2f}".format(
                pts[i]["lon"], pts[i]["lat"], pts[i]["alt"]))
            i += 1
        out.append('    <Placemark><styleUrl>#s{}</styleUrl>'
                   '<LineString><tessellate>1</tessellate>'
                   '<altitudeMode>clampToGround</altitudeMode>'
                   '<coordinates>{}</coordinates></LineString></Placemark>'
                   .format(band, " ".join(coords)))
    out.append('  </Folder></Document></kml>')
    with open(path, "w", encoding="utf-8") as f:
        f.write("\n".join(out))


def pick_file_dialog():
    """Open a file-open dialog; return path or None. Falls back to input()."""
    try:
        import tkinter as tk
        from tkinter import filedialog
        root = tk.Tk()
        root.withdraw()
        path = filedialog.askopenfilename(
            title="Select your NMEA file",
            filetypes=[("NMEA / text files", "*.nmea *.txt *.log *.csv"),
                       ("All files", "*.*")])
        root.destroy()
        return path or None
    except Exception:
        try:
            return input("NMEA file path: ").strip().strip('"') or None
        except EOFError:
            return None


def show_summary(msg):
    """Show a popup if possible; always print to console too."""
    print(msg)
    try:
        import tkinter as tk
        from tkinter import messagebox
        root = tk.Tk()
        root.withdraw()
        messagebox.showinfo("Done", msg)
        root.destroy()
    except Exception:
        pass


def main():
    # Path from command line if given, otherwise open a dialog.
    if len(sys.argv) > 1:
        in_path = sys.argv[1]
    else:
        in_path = pick_file_dialog()

    if not in_path or not os.path.isfile(in_path):
        show_summary("No valid file selected.")
        return

    pts = read_points(in_path)
    if len(pts) < 2:
        show_summary("Need at least 2 valid GGA fixes to compute speed.\n"
                     "Check that the file contains GGA sentences with a fix.")
        return

    compute_speeds(pts)
    smooth_speeds(pts, SMOOTH_WINDOW)

    base = os.path.splitext(in_path)[0]
    csv_path = base + ".csv"
    kml_path = base + "_speed.kml"

    speeds_kmh = [p["v"] * 3.6 for p in pts]
    vmax = max(speeds_kmh)
    total_dist = sum(p["dist"] for p in pts)
    total_time = sum(p["dt"] for p in pts)
    avg_kmh = (total_dist / total_time * 3.6) if total_time > 0 else 0.0

    write_csv(pts, csv_path)
    write_kml(pts, kml_path, vmax if vmax > 0 else 1.0)

    msg = ("Fixes used      : {}\n"
           "Total distance  : {:.1f} m ({:.3f} km)\n"
           "Duration        : {:.1f} s\n"
           "Average speed   : {:.2f} km/h\n"
           "Max speed       : {:.2f} km/h\n\n"
           "CSV : {}\n"
           "KML : {}").format(
        len(pts), total_dist, total_dist / 1000.0, total_time,
        avg_kmh, vmax, csv_path, kml_path)
    show_summary(msg)


if __name__ == "__main__":
    main()