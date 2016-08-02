#!/bin/sh

sudo ../s2i build file:///home/osboxes/test/rest-server cpp-build rest-server --runtime-image cpp-run --runtime-artifact /app
