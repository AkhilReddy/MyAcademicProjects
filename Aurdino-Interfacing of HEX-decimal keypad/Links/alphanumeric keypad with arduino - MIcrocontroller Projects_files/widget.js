(function(theWindow) {
  var Swiftype = theWindow.Swiftype || (theWindow.Swiftype = {});
  Swiftype.root_url = Swiftype.root_url || "//api.swiftype.com";
  Swiftype.key = "Wh71v6a7P1ce4B6_TVvs";
  Swiftype.inputElement = "#st-search-input";
  Swiftype.attachElement = "#st-search-input";
  Swiftype.renderStyle = "inline";
  Swiftype.searchPerPage = 10;
  Swiftype.autocompleteResultLimit = 10;

  // Unset optional configuration that may have been set by the old embed or attempted customization
  Swiftype.resultPageURL = undefined;
  Swiftype.resultContainingElement = null;
  Swiftype.disableAutocomplete = false;


  Swiftype.resultContainingElement = "#st-results-container";


  var executeCommand = theWindow[theWindow["SwiftypeObject"]];

  executeCommand("loadStyleSheet", "//s.swiftypecdn.com/assets/swiftype-372b0eab2251b5551acc7e940f39a528.css");
  executeCommand("loadScript", "//s.swiftypecdn.com/assets/swiftype_onpage-86496bf10a8dcb21f124b42b0b9a91b5.js");

})(window);
