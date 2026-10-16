/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilo <lilo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:30:46 by lilo              #+#    #+#             */
/*   Updated: 2026/10/16 14:15:57 by lilo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int handle_calculated_burnout(t_coder *coder)
{
    t_whiteboard    *whiteboard; 

    whiteboard = coder->check_whiteboard_ptr;
    usleep(whiteboard->time_to_burnout - coder->time_last_compiled);
    if (pthread_mutex_lock(&whiteboard->burnt_mutex) != 0)
        return (write_error("Failed to lock burnt_mutex",
            MUTEX_ERROR), ERROR);
    if (log_activity(coder, "burned out") != OK)
        return (ERROR);
    if (pthread_mutex_unlock(&whiteboard->burnt_mutex) != 0)
        return (write_error("Failed to unlock burnt_mutex",
            MUTEX_ERROR), ERROR);
    whiteboard->is_burnt = TRUE;
}
