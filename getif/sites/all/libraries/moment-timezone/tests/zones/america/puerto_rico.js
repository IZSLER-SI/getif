"use strict";

var helpers = require("../../helpers/helpers");

exports["America/Puerto_Rico"] = {

	"guess:by:offset" : helpers.makeTestGuess("America/Puerto_Rico", { offset: true, expect: "America/Santo_Domingo" }),

	"guess:by:abbr" : helpers.makeTestGuess("America/Puerto_Rico", { abbr: true, expect: "America/Santo_Domingo" }),

	"1942" : helpers.makeTestYear("America/Puerto_Rico", [
		["1942-05-03T03:59:59+00:00", "23:59:59", "AST", 240],
		["1942-05-03T04:00:00+00:00", "01:00:00", "AWT", 180]
	]),

	"1945" : helpers.makeTestYear("America/Puerto_Rico", [
		["1945-08-14T22:59:59+00:00", "19:59:59", "AWT", 180],
		["1945-08-14T23:00:00+00:00", "20:00:00", "APT", 180]
	])
};