# LEIC-A-IST #

#### Projects and Scripts from computer science classes ####

## Table of Contents: ##

- 1st semester:

  * FP (Programming Fundamentals)
  * IAC (Introduction to Computer Architeture)

- 2nd semester

  * LP (Logic for Programming)
  * IAED (Introduction to Algorithms and Data Structures)

#### Attention: The majority of the content here is in portuguese or has portuguese documentation. If a translation is needed, feel free to contact me / submit an issue. ####


## Repo rules/organization ##

-	Each discipline/course/"cadeira" that has coding assignements
	and or projects shall have a folder in the repo.

-	All the lab / practice classes shall be under a subfolder,
	under the name "LAB".

-	In lab classes, the question papers and related material must be
	kept in the same dir as the answers (see IAED/FP). If the
	questions papers are all in the same file, it shall be placed on
	the root dir of all the folders containing each week's answers.
	(see IAC).

-	All the projects shall be under folders named "Proj" or "Proj@",
	where "@" is the number of the project. If available, the
	automatic tests shall be kept, zipped, for future reference.

-	If, in the course of the semester, a content tracker was used,
	its history shall be protected, using zip compression; but a
	copy of the work must be put uncompressed on the repo (usually,
	the latest state of that repo) (see IAED/Archive/LAB.zip).
	If a cruder way of work management was used (shared folder,
	with chronological dates), it shall also be archived as-is;
	additionaly, it shall be added to the repo in chronological
	order, using a new branch, and then it shall be commited to
	the main branch.

-	In any file or folder where numeration is present and / or
	necessary, it shall employ the following numbering scheme:

	-	Number of digits employed = Number of digits of the
		highest number in use. E.g.:
		
		-	3   folder  -> 1/, 2/, 3/                   (see IAC/LAB)
		-	12  folders -> 01/, 02/, ..., 23/          (see IAED/LAB)
		-	101 folders -> 001, 002/, ..., 023/, ..., 101/

-	If the course/class book is available, it shall be in the class
	folder, under its name (see FP/Programacao em Python; LP/Logica
	e Raciocinio).

-	The file formats generally allowed are:

	-  text;
	-  zip;
	-  pdf.

	Other file formats are accepted in this repo (see IAC/
	scripts_apoio/p3sim.jar), but if and only if they are essential
	to the completedness of this repo, and do not incur in danger
	of being "unopenable" in the next 20 years. If possible, all
	other file formats shall be transformed in one of those above
	mentioned (example: convertig from mhtml to pdf).

