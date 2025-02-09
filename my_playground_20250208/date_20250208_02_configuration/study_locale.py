# import locale

# # Get the current locale
# current_locale = locale.getlocale(locale.LC_CTYPE)
# print(f"Current LC_CTYPE: {current_locale}")

# # Set a new locale
# locale.setlocale(locale.LC_CTYPE, "C")
# print(f"New LC_CTYPE: {locale.getlocale(locale.LC_CTYPE)}")



# import locale
# import string

# # Set to C locale
# locale.setlocale(locale.LC_CTYPE, "C")
# print("locale.LC_CTYPE :", locale.getlocale(locale.LC_CTYPE))
# print("C Locale:")
# print("Is 'é' a letter?", "é".isalpha())  # False in C locale

# # Set to UTF-8 locale
# locale.setlocale(locale.LC_CTYPE, "en_US.UTF-8")
# print("locale.LC_CTYPE :", locale.getlocale(locale.LC_CTYPE))
# print("UTF-8 Locale:")
# print("Is 'é' a letter?", "é".isalpha())  # True in UTF-8 locale


import locale

locale.setlocale(locale.LC_CTYPE, "C")
print("locale.LC_CTYPE :", locale.getlocale(locale.LC_CTYPE))
print("C Locale:")
print("Uppercase of 'é':", "é".upper())  # No change in C locale

locale.setlocale(locale.LC_CTYPE, "en_US.UTF-8")
print("locale.LC_CTYPE :", locale.getlocale(locale.LC_CTYPE))
print("UTF-8 Locale:")
print("Uppercase of 'é':", "é".upper())  # Converts to 'É'
