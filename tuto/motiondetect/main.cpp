/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpark <>                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 14:48:42 by cpark             #+#    #+#             */
/*   Updated: 2017/05/15 14:48:42 by cpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lib.h"

int	dist(int x1, int y1)
{
	return (sqrt((x1 - y1)^2));
}

int	main(int ac, char **av)
{
	Mat		image;
	Mat		prev_image;
	Mat		gray_p;
	Mat		gray;
	VideoCapture	cap;
	int		threshold = 5;
	int		x;
	int		y;

	cap.open(0);
	cap.read(prev_image);
	while (1)
	{
		cap.read(image);
		cvtColor(prev_image, gray_p, CV_BGR2GRAY);
		cvtColor(image, gray, CV_BGR2GRAY);
		x = 0;
		while (x < image.cols)
		{
			y = 0;
			while (y < image.rows)
			{
				if (dist(gray.data[x + y * image.cols], gray_p.data[x + y * image.cols]) < threshold)
					gray.data[x + y * image.cols] = 255;
				else
					gray.data[x + y * image.cols] = 0;
				y++;
			}
			x++;
		}
		imshow("live", gray);
		if (waitKey(10) == 27)
			break ;
		prev_image = image.clone();
	}
}
