// $(document).ready(function() {
// 	$(".desktop1").show();
// 	$(".desktop2").hide();
// 	$(".desktop3").hide();
// 	$(".desktop4").hide();
// 	$(".right_side").click(function() {
// 		if($(".desktop1").is(":visible")) {
// 			//$(".desktop1").animate({width: "toggle"});
// 			//$(".desktop2").animate({width: "toggle"});
// 			$(".desktop2").animate({width: "toggle"}, 1000, function() {
// 				$(".desktop1").hide();
// 			});
// 			//$(".desktop2").animate({width: 0});
// 		} else if($(".desktop2").is(":visible")) {
// 			// $(".desktop2").hide();
// 			// $(".desktop3").show();
// 			$(".desktop3").animate({width: "toggle"}, 1000, function() {
// 				$(".desktop2").hide();
// 			});
// 		} else if($(".desktop3").is(":visible")) {
// 			// $(".desktop3").hide();
// 			// $(".desktop4").show();
// 			$(".desktop4").animate({width: "toggle"}, 1000, function() {
// 				$(".desktop3").hide();
// 			});
// 		}
// 	});
// 	$(".left_side").click(function() {
// 		if($(".desktop2").is(":visible")) {
// 			// $(".desktop2").hide();
// 			// $(".desktop1").show();
// 			$(".desktop1").show();
// 			$(".desktop2").animate({width: "toggle"}, 1000, function() {
// 				$(".desktop2").hide();
// 			});
// 		} else if($(".desktop3").is(":visible")) {
// 			// $(".desktop3").hide();
// 			// $(".desktop2").show();
// 			$(".desktop2").show();
// 			$(".desktop3").animate({width: "toggle"}, 1000, function() {
// 				$(".desktop3").hide();
// 			});
// 		} else if($(".desktop4").is(":visible")) {
// 			// $(".desktop4").hide();
// 			// $(".desktop3").show();
// 			$(".desktop3").show();
// 			$(".desktop4").animate({width: "toggle"}, 1000, function() {
// 				$(".desktop4").hide();
// 			});
// 		}
// 	});
// });
$(document).ready(function() {
	$(".desktop1").show();
	$(".desktop2").hide();
	$(".desktop3").hide();
	$(".desktop4").hide();

	var clickDisabled = false;

	$(".right_side").click(function(e) {
		e.preventDefault();

		if (clickDisabled) {
			return;
		}

		if($(".desktop1").is(":visible")) {
			$(".desktop1").css({'right': '0', 'left': ''}).animate({'right':'100%'}, 1000, function() {
				$(".desktop1").hide();
			});
			$(".desktop2").css({'right': '', 'left': '100%'}).show().animate({'left':'0'}, 1000, function() {});
		} else if($(".desktop2").is(":visible")) {
			$(".desktop2").css({'right': '0', 'left': ''}).animate({'right':'100%'}, 1000, function() {
				$(".desktop2").hide();
			});
			$(".desktop3").css({'right': '', 'left': '100%'}).show().animate({'left':'0'}, 1000, function() {});
		} else if($(".desktop3").is(":visible")) {
			$(".desktop3").css({'right': '0', 'left': ''}).animate({'right':'100%'}, 1000, function() {
				$(".desktop3").hide();
			});
			$(".desktop4").css({'right': '', 'left': '100%'}).show().animate({'left':'0'}, 1000, function() {});
		}

		clickDisabled = true;
		setTimeout(function(){clickDisabled = false;}, 1000);
	});
	$(".left_side").click(function(e) {
		e.preventDefault();

		if (clickDisabled) {
			return;
		}

		if($(".desktop2").is(":visible")) {
			$(".desktop1").css({'right': '100%', 'left': ''}).show().animate({'right':'0'}, 1000, function() {});
			$(".desktop2").css({'right': '', 'left': '0'}).animate({'left':'100%'}, 1000, function() {
				$(".desktop2").hide();
			});
		} else if($(".desktop3").is(":visible")) {
			$(".desktop2").css({'right': '100%', 'left': ''}).show().animate({'right':'0'}, 1000, function() {});
			$(".desktop3").css({'right': '', 'left': '0'}).animate({'left':'100%'}, 1000, function() {
				$(".desktop3").hide();
			});
			
		} else if($(".desktop4").is(":visible")) {
			$(".desktop3").css({'right': '100%', 'left': ''}).show().animate({'right':'0'}, 1000, function() {});
			$(".desktop4").css({'right': '', 'left': '0'}).animate({'left':'100%'}, 1000, function() {
				$(".desktop4").hide();
			});
		}

		clickDisabled = true;
		setTimeout(function(){clickDisabled = false;}, 1000);

	});
});